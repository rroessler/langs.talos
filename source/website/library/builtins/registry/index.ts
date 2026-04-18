/// Node Modules
import * as fs from 'node:fs';

/// Vendor Modules
import * as JSONC from 'jsonc-parser';

/// Website Modules
import { Assets } from '@/website/assets';

/// Package Modules
import { Property } from '../property';
import { Ancillary, Descriptor } from '../descriptor';

/** Builtins Registry Namespace. */
export namespace Registry {
    //  TYPEDEFS  //

    /** Internal Replacement Interface. */
    interface Replacer {
        readonly re: string;
        readonly pp: string;
    }

    //  PROPERTIES  //

    /** Replacements factory to be used. */
    const m_replacements = (type: string): Replacer[] => [
        { re: `TALOS_XX_${type}_HEADER\\(\\)`, pp: '{' },
        { re: `TALOS_XX_${type}_DEFINE\\((\\w+)\\)`, pp: '"name": "$1",' },
        { re: `TALOS_XX_${type}_TYPEDEF\\("([^"]*)"\\)`, pp: '"typedef": "$1",' },
        { re: `TALOS_XX_${type}_DESCRIBE\\("([^"]*)"\\)`, pp: '"describe": "$1",' },
        { re: `TALOS_XX_${type}_FOOTER\\(\\)`, pp: '},' },
    ];

    //  PUBLIC METHODS  //

    /** Resolves a list of all builtins. */
    export function list(): Descriptor[] {
        // prepare the source directory of builtins
        const source = Assets.builtins();

        // prepare the resolved items
        const resolved = fs.readdirSync(source).map((name) => resolve(name));

        // filter all the available files now
        return resolved.filter(m_filter);
    }

    /**
     * Handles resolving builtin documentation.
     * @param name                  Name of builtin.
     * @param extra                 Extra details.
     */
    export function resolve(name: string, extra?: Ancillary): Descriptor | undefined {
        // attempt finding the necessary builtin now
        const builtin = Assets.builtins(name, 'index.mdx');
        if (name.startsWith('_') || !fs.existsSync(builtin)) return;

        // get the underlying definition files now
        const fields = m_process(name, 'fields', extra);
        const statics = m_process(name, 'statics', extra);

        // resolve the descriptor now
        return { ...m_details(name), fields, statics };
    }

    //  PRIVATE METHODS  //

    /**
     * Handles filtering builtins.
     * @param builtin               Builtin to filter.
     */
    function m_filter(builtin?: Descriptor): builtin is Descriptor {
        return typeof builtin === 'object';
    }

    /**
     * Handles resolving descriptors traits.
     * @param name                  Name of builtin.
     */
    function m_details(name: string): Descriptor {
        const traits = Assets.builtins(name, '_defines', 'traits.json');
        if (!fs.existsSync(traits)) return { name: name[0].toUpperCase() + name.slice(1) };
        return JSONC.parse(fs.readFileSync(traits, 'utf-8')); // can safely resolve here
    }

    /**
     * Handles processing helper files.
     * @param name                  Name of builtin.
     * @param type                  Type of details.
     * @param extras                Extras to bind.
     */
    function m_process(name: string, type: 'fields' | 'statics', extras?: Ancillary) {
        // prepare the baseline definition string to be transformed
        const defines = Assets.builtins(name, '_defines', `${type}.def`);

        // if the file does not exist, then stop handling
        if (!fs.existsSync(defines)) return;

        // attempt processing the incoming content
        let content = fs.readFileSync(defines, 'utf-8');

        // handle processing the incoming content
        const replacements = m_replacements(type.toUpperCase());

        // iterate over the available replacements to execute
        for (const { re, pp } of replacements) content = content.replaceAll(new RegExp(re, 'g'), pp);

        // and parse the incoming results now
        return JSONC.parse(`[${content}]`).map(
            (property: Property): Property => ({
                ...property, // merge the extra details now
                ancillary: extras?.[`${type}.${property.name}`],
            }),
        );
    }
}
