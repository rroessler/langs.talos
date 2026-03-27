/// Node Modules
import * as fs from 'node:fs';

/// Website Modules
import { Assets } from '@/website/assets';

/// Package Modules
import { Descriptor } from '../descriptor';

/** Builtins Registry Namespace. */
export namespace Registry {
    //  PUBLIC METHODS  //

    /** Resolves a list of all builtins. */
    export function list(): Descriptor[] {
        // prepare the source directory of builtins
        const source = Assets.builtins();

        // filter all the available files now
        return fs
            .readdirSync(source)
            .map(resolve)
            .filter((builtin): builtin is Descriptor => typeof builtin === 'object');
    }

    /**
     * Handles resolving builtin documentation.
     * @param name                  Name of builtin.
     */
    export function resolve(name: string): Descriptor | undefined {
        // attempt finding the necessary builtin now
        const builtin = Assets.builtins(name, 'index.mdx');
        if (name.startsWith('_') || !fs.existsSync(builtin)) return;

        // since value, then resolve a suitable set of details
        return { name: name[0].toUpperCase() + name.slice(1) };
    }
}
