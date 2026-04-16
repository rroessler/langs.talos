/// Node Modules
import * as fs from 'node:fs';
import * as path from 'node:path';

/// Website Modules
import { Assets } from '@/website/assets';
import { Product } from '@/website/product';

/// Package Modules
import { Manifest } from '../manifest';

/** Crates Registry Namespace. */
export namespace Registry {
    //  PUBLIC METHODS  //

    /** Resolves a list of all crates. */
    export function list(): Manifest[] {
        // prepare the source directory of crates
        const source = Assets.crates();

        // filter all the available files now
        return fs
            .readdirSync(source)
            .map(resolve)
            .filter((crate): crate is Manifest => typeof crate === 'object');
    }

    /**
     * Handles resolving crate manifests.
     * @param name                  Name of crate.
     */
    export function resolve(name: string): Manifest | undefined {
        const prefix = `${Product.identifier}:`; // prepare the prefix now
        name = name.startsWith(prefix) ? name.slice(prefix.length) : name;

        // attempt finding the necessary crate now
        const crate = Assets.crates(name, '_crate.jsonc');
        if (name.startsWith('_') || !fs.existsSync(crate)) return;

        // prepare a suitable resolution handler now
        const resolve = (...segments: string[]) => path.resolve(crate, '..', ...segments);

        // attempt parsing the incoming JSONC file now
        return { ...JSON.parse(fs.readFileSync(crate, 'utf-8')), resource: crate, resolve };
    }
}
